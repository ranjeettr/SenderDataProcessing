TOP_DIR=.
BUILD_DIR=build

.PHONY: all
all:
	if [ ! -d "${TOP_DIR}/${BUILD_DIR}" ]; then \
		mkdir ${TOP_DIR}/${BUILD_DIR}; \
	fi

	cmake -S ${TOP_DIR} -B ${BUILD_DIR}
	make -C ${BUILD_DIR}

.PHONY: clean
clean:
	rm -rf ${BUILD_DIR}
