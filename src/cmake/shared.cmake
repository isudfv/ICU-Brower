set(SHARED_INCLUDE_PATH
        ${CMAKE_SOURCE_DIR}/src/shared/ad-block
        ${CMAKE_SOURCE_DIR}/src/shared/browser
        ${CMAKE_SOURCE_DIR}/src/shared/window
        ${CMAKE_SOURCE_DIR}/src/shared/download
		${CMAKE_SOURCE_DIR}/src/shared/favorites
		${CMAKE_SOURCE_DIR}/src/shared/history
		${CMAKE_SOURCE_DIR}/src/shared/user)

set(SHARED_HISTORY_SRCS
		${CMAKE_SOURCE_DIR}/src/shared/history/historymanager.cpp
		${CMAKE_SOURCE_DIR}/src/shared/history/historymanager.h)

set(SHARED_BROWSER_SRCS
        ${CMAKE_SOURCE_DIR}/src/shared/browser/browserclient.cc
        ${CMAKE_SOURCE_DIR}/src/shared/browser/browserclient.h
        ${CMAKE_SOURCE_DIR}/src/shared/browser/clienthandler.cc
        ${CMAKE_SOURCE_DIR}/src/shared/browser/clienthandler.h)

set(SHARED_WINDOW_SRCS
#        ${CMAKE_SOURCE_DIR}/src/shared/window/qbrowserwindow.cc
#        ${CMAKE_SOURCE_DIR}/src/shared/window/qbrowserwindow.h
        ${CMAKE_SOURCE_DIR}/src/shared/window/windowmanager.cpp
        ${CMAKE_SOURCE_DIR}/src/shared/window/windowmanager.h
)


set(SHARED_DOWNLOAD_SRCS
		${CMAKE_SOURCE_DIR}/src/shared/download/downloaditem.cc
		${CMAKE_SOURCE_DIR}/src/shared/download/downloaditem.h
		${CMAKE_SOURCE_DIR}/src/shared/download/downloadmanager.cpp
		${CMAKE_SOURCE_DIR}/src/shared/download/downloadmanager.h)

set(SHARED_FAVORITES_SRCS
		${CMAKE_SOURCE_DIR}/src/shared/favorites/favoritesmanager.cpp
		${CMAKE_SOURCE_DIR}/src/shared/favorites/favoritesmanager.h)

set(SHARED_USER_SRCS
        ${CMAKE_SOURCE_DIR}/src/shared/user/usermanager.cpp
        ${CMAKE_SOURCE_DIR}/src/shared/user/usermanager.h)

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
