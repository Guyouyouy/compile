SET(LIBHELLO_SRC hello.c)
ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})
ADD_LIBRARY(hello_static STATIC ${LIBHELLO_SRC})
SET_TARGET_PROPERTIES(hello_static PROPERTIES OUTPUT_NAME "hello")

SET_TARGET_PROPERTIES(hello PROPERTIES VERSION 1.2 SOVERSION 1)

INSTALL(TARGETS hello hello_static LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
INSTALL(FILES hello.h DESTINATION include/hello)

#注意以下内容删掉，不是CMakeLists内容，是install位置，执行make install后，一个展示效果
Install the project...
-- Install configuration: ""
-- Installing: /usr/lib/libhello.so.1.2
-- Installing: /usr/lib/libhello.so.1
-- Installing: /usr/lib/libhello.so
-- Installing: /usr/lib/libhello.a
-- Installing: /usr/include/hello/hello.h
