PROJECT(TEXTMININGCOMPILER)

file(
	GLOB_RECURSE
	source_files
	*.cc *.hh
)

add_executable(
	TextMiningCompiler
	main.cc
	${source_files}
)
