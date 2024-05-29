
run_1.explicit:
	g++ -std=c++17 ./1.explicit.cpp -o ./build/1.explicit -g && ./build/1.explicit

run_2.exception:
	g++ -std=c++17 ./2.exception.cpp -o ./build/2.exception -g && ./build/2.exception

run_3.asio:
	g++ -std=c++17 ./3.boost_asio.cpp -o ./build/3.boost_asio -g && ./build/3.boost_asio