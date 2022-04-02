BUILD_DIR=build
REPORT_DIR=${BUILD_DIR}/report
PROJECT_DIR=~/Dev/CLionProjects/task2

.PHONY: all

clean:
	rm -rf ${BUILD_DIR}

sync: clean
	cmake -B ${BUILD_DIR} -DENABLE_SANITIZERS=ON -DENABLE_TESTS=ON
	cmake --build ${BUILD_DIR}
	./${BUILD_DIR}/task2 -l -40 -h 40 -s 104857600

async: clean
	cmake -B ${BUILD_DIR} -DENABLE_SANITIZERS=ON -DENABLE_TESTS=ON -DENABLE_ASYNC=ON
	cmake --build ${BUILD_DIR}
	./${BUILD_DIR}/task2 -l -40 -h 40 -s 104857600

valgrind: clean
	cmake -B ${BUILD_DIR} -DENABLE_TESTS=ON
	cmake --build ${BUILD_DIR}
	valgrind --error-exitcode=1 --read-var-info=yes --leak-check=full --show-leak-kinds=all ${BUILD_DIR}/libs/buffer_lib/tests/buffer_test ${BUILD_DIR}/libs/temperature_lib/tests/temperature_test

test: clean
	cmake -B ${BUILD_DIR} -DENABLE_SANITIZERS=ON -DENABLE_TESTS=ON -DENABLE_COVERAGE=ON
	make -C ${BUILD_DIR} all test

coverage: test
	lcov --capture --directory ${BUILD_DIR} --exclude "/usr/*" --exclude "11.2.0/*" --output-file ${BUILD_DIR}/coverage.info
	genhtml -o ${BUILD_DIR}/report ${BUILD_DIR}/coverage.info

docker:
	docker run -v ${PROJECT_DIR}:/home/project -it zeronethunter/task1:latest

check:
	./scripts/check.sh