# make

```
@Def(file: make.cpp)
	@put(globals)
	int main(int argc, const char *argv[]) {
		@put(main)
	}
@End(file: make.cpp)
```

```
@inc(stack.md)
```

```
@add(globals)
	#include <iostream>
@end(globals)
```

```
@add(globals)
	bool continues_to_next_line(const std::string &line) {
		return ! line.empty() && line.back() == '\\';
	}
@end(globals)
```

```
@add(globals)
	std::string merge_lines(std::string first, std::string next) {
		int non_space { 0 };
		while (non_space < next.size() && next[non_space] == '\t') {
			++non_space;
		}
		return
			first.substr(0, first.size() - 1) +
			next.substr(non_space);
	}
@end(globals)
```

```
@def(main)
	File_Stack makefiles;
	makefiles.push("Makefile");
	std::string line;
	try { for (;;) {
		makefiles.get_line(line);
		if (line.empty()) { continue; }
		while (continues_to_next_line(line)) {
			std::string next;
			makefiles.get_line(next);
			line = merge_lines(line, next);
		}
		std::cout << line << "\n";
	} } catch (
		const File_Stack::End_Reached &
	) {
		if (continues_to_next_line(line)) {
			std::cerr << makefiles << " ends with continuing line\n";
		}
	}
@end(main)
```

