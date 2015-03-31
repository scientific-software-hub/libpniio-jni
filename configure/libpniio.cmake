pkg_search_module(LIBPNIIO_PKG REQUIRED pniio)

#add compiler definitions
add_definitions(${LIBPNIIO_PKG_CFLAGS})

#add include directories
include_directories(${LIBPNIIO_PKG_INCLUDE_DIRS})

#add lib directories
link_directories(${LIBPNIIO_PKG_LIBRARY_DIRS})