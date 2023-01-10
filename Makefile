
ALL:
	gcc timer.c list.c -c
	ar rcs libtimer.a *.o

	g++ test_timer.cc -ltimer -fpermissive -std=c++11 -o test_timer

clean:
	rm -rf libtimer.a *.o a.out test_timer
