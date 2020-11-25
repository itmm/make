# Stack of open input files

```
@Def(globals)
	@put(globals)
	class File_Stack {
		@put(privates)
	public:
		@put(publics)
	};
@End(globals)
```

```
@def(globals)
	#include <string>
@end(globals)
```

```
@def(publics)
	@put(needed by get line)
	std::string &get_line(
		std::string &line
	) {
		@put(get line)
		return line;
	}
@end(publics)
```

```
@def(needed by get line)
	class End_Reached {};
@end(needed by get line)
```

```
@add(globals)
	#include <fstream>
	#include <memory>
	#include <stack>
@end(globals)
```

```
@def(privates)
	struct Open_File {
		const std::string path;
		std::unique_ptr<std::ifstream> file;
		unsigned line = 0;
		Open_File(const std::string &path):
			path { path },
			file { new std::ifstream { path.c_str() } }
		{ }
	};
	std::stack<Open_File> stack_;
@end(privates)
```

```
@def(get line)
	while (! stack_.empty()) {
		@put(try to get line)
	}
	throw End_Reached { };
@end(get line)
```

```
@add(publics)
	void push(const std::string &path) {
		stack_.emplace(path);
	}
@end(publics)
```

```
@def(try to get line)
	auto &top { stack_.top() };
	if (std::getline(*top.file, line)) {
		++top.line;
		return line;
	} else {
		stack_.pop();
	}
@end(try to get line)
```

```
@add(publics)
	void write_pos(
		std::ostream &out
	) const {
		if (! stack_.empty()) {
			auto &top { stack_.top() };
			out << top.path <<
				':' << top.line << ':';
		} else {
			out << "no file:";
		}
	}
@end(publics)
```

```
@Add(globals)
	std::ostream &operator<<(
		std::ostream &out,
		const File_Stack &stack
	) {
		stack.write_pos(out);
		return out;
	}
@End(globals)
```
