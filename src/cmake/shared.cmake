set(SHARED_INCLUDE_PATH
        ${CMAKE_SOURCE_DIR}/src/shared/ad-block
        ${CMAKE_SOURCE_DIR}/src/shared/browser
        ${CMAKE_SOURCE_DIR}/src/shared/window
        ${CMAKE_SOURCE_DIR}/src/shared/download
		${CMAKE_SOURCE_DIR}/src/shared/favorites)

set(SHARED_BROWSER_SRCS
        ${CMAKE_SOURCE_DIR}/src/shared/browser/browserclient.cc
        ${CMAKE_SOURCE_DIR}/src/shared/browser/browserclient.h
        ${CMAKE_SOURCE_DIR}/src/shared/browser/clienthandler.cc
        ${CMAKE_SOURCE_DIR}/src/shared/browser/clienthandler.h)

set(SHARED_WINDOW_SRCS
        ${CMAKE_SOURCE_DIR}/src/shared/window/qbrowserwindow.cc
        ${CMAKE_SOURCE_DIR}/src/shared/window/qbrowserwindow.h)


set(SHARED_DOWNLOAD_SRCS
		${CMAKE_SOURCE_DIR}/src/shared/download/qdownloadwidget.cpp
		${CMAKE_SOURCE_DIR}/src/shared/download/qdownloadwidget.h
		${CMAKE_SOURCE_DIR}/src/shared/download/qdownloadwidget.ui)

set(SHARED_BOOKMARKS_SRCS
        ${CMAKE_SOURCE_DIR}/src/shared/favorites/favoritesmanager.cpp
		${CMAKE_SOURCE_DIR}/src/shared/favorites/favoritesmanager.h
	)

set(WINDOWS_MANIFEST_DIR
        ${CMAKE_SOURCE_DIR}/src/shared/manifest)

set(SHARED_AB_BLOCK_SRCS
        ${CMAKE_SOURCE_DIR}/src/shared/ad-block/ad_block_client.h
        ${CMAKE_SOURCE_DIR}/src/shared/ad-block/ad_block_client.cc
        ${CMAKE_SOURCE_DIR}/src/shared/ad-block/no_fingerprint_domain.cc
        ${CMAKE_SOURCE_DIR}/src/shared/ad-block/filter.cc
        ${CMAKE_SOURCE_DIR}/src/shared/ad-block/protocol.cc
        ${CMAKE_SOURCE_DIR}/src/shared/ad-block/context_domain.cc
        ${CMAKE_SOURCE_DIR}/src/shared/ad-block/cosmetic_filter.cc
        ${CMAKE_SOURCE_DIR}/src/shared/ad-block/BloomFilter.cpp
        ${CMAKE_SOURCE_DIR}/src/shared/ad-block/hash_set.cc
        ${CMAKE_SOURCE_DIR}/src/shared/ad-block/hashFn.cc)