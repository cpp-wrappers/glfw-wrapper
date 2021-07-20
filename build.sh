mkdir -p build/objects

compile() {
	if ! $CXX -c --config ./compile_flags.txt -o build/objects/$1.o src/$1.cpp
		then exit 1
	fi

	ar -vcr build/libglfw-wrapper.a build/objects/$1.o
}

compile error
compile library
compile window