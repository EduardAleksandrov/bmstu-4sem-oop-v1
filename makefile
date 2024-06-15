
run_1.explicit:
	g++ -std=c++17 ./1.explicit.cpp -o ./build/1.explicit -g && ./build/1.explicit

run_2.exception:
	g++ -std=c++17 ./2.exception.cpp -o ./build/2.exception -g && ./build/2.exception

run_3.ref:
	g++ -std=c++17 ./3.ref.cpp -o ./build/3.ref -g && ./build/3.ref

run_4.tmp:
	g++ -std=c++17 ./4.tmp.cpp -o ./build/4.tmp -g && ./build/4.tmp

run_5.inheritance:
	g++ -std=c++17 ./5.inheritance.cpp -o ./build/5.inheritance -g && ./build/5.inheritance

run_5.1.inh:
	g++ -std=c++17 ./5.1.inh.cpp -o ./build/5.1.inh -g && ./build/5.1.inh

run_6.uptr:
	g++ -std=c++17 ./6.uptr.cpp -o ./build/6.uptr -g && ./build/6.uptr

run_7.uptr2:
	g++ -std=c++17 ./7.uptr2.cpp -o ./build/7.uptr2 -g && ./build/7.uptr2

run_8.iter:
	g++ -std=c++17 ./8.iter.cpp -o ./build/8.iter -g && ./build/8.iter

run_9.type:
	g++ -std=c++17 ./9.type.cpp -o ./build/9.type -g && ./build/9.type