PROJECT(TEXTMININGCOMPILER)

file(
	GLOB_RECURSE
	source_files
	src/*
)

add_executable(
	TextMiningCompiler
	main.cpp
	${source_files}
)