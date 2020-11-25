
#line 4 "index.md"

	
#line 4 "stack.md"

	
#line 15 "stack.md"

	#include <string>

#line 39 "stack.md"

	#include <fstream>
	#include <memory>
	#include <stack>

#line 5 "stack.md"

	class File_Stack {
		
#line 47 "stack.md"

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

#line 7 "stack.md"

	public:
		
#line 21 "stack.md"

	
#line 33 "stack.md"

	class End_Reached {};

#line 22 "stack.md"

	std::string &get_line(
		std::string &line
	) {
		
#line 62 "stack.md"

	while (! stack_.empty()) {
		
#line 79 "stack.md"

	auto &top { stack_.top() };
	if (std::getline(*top.file, line)) {
		++top.line;
		return line;
	} else {
		stack_.pop();
	}

#line 64 "stack.md"

	}
	throw End_Reached { };

#line 26 "stack.md"

		return line;
	}

#line 71 "stack.md"

	void push(const std::string &path) {
		stack_.emplace(path);
	}

#line 91 "stack.md"

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

#line 9 "stack.md"

	};

#line 107 "stack.md"

	std::ostream &operator<<(
		std::ostream &out,
		const File_Stack &stack
	) {
		stack.write_pos(out);
		return out;
	}

#line 17 "index.md"

	#include <iostream>

#line 23 "index.md"

	bool continues_to_next_line(const std::string &line) {
		return ! line.empty() && line.back() == '\\';
	}

#line 31 "index.md"

	std::string merge_lines(std::string first, std::string next) {
		int non_space { 0 };
		while (non_space < next.size() && next[non_space] == '\t') {
			++non_space;
		}
		return
			first.substr(0, first.size() - 1) +
			next.substr(non_space);
	}

#line 5 "index.md"

	int main(int argc, const char *argv[]) {
		
#line 45 "index.md"

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

#line 7 "index.md"

	}
