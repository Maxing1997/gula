include(CheckFunctionExists)

check_function_exists(accept4 HAVE_ACCEPT4)
if(NOT HAVE_ACCEPT4)
  set_source_files_properties(SocketsOps.cc PROPERTIES COMPILE_FLAGS "-DNO_ACCEPT4")
endif()

set(net_SRCS
  Acceptor.cc
  Buffer.cc
  Channel.cc
  Connector.cc
  EventLoop.cc
  EventLoopThread.cc
  EventLoopThreadPool.cc
  InetAddress.cc
  Poller.cc
  poller/DefaultPoller.cc
  poller/EPollPoller.cc
  poller/PollPoller.cc
  Socket.cc
  SocketsOps.cc
  TcpClient.cc
  TcpConnection.cc
  TcpServer.cc
  Timer.cc
  TimerQueue.cc
  )

add_library(gula_net ${net_SRCS})
target_link_libraries(gula_net gula_base)


install(TARGETS gula_net DESTINATION lib)

set(HEADERS
  Buffer.h
  Callbacks.h
  Channel.h
  Endian.h
  EventLoop.h
  EventLoopThread.h
  EventLoopThreadPool.h
  InetAddress.h
  Poller.cc
  poller/DefaultPoller.cc
  poller/EPollPoller.cc
  poller/PollPoller.cc
  TcpClient.h
  TcpConnection.h
  TcpServer.h
  TimerId.h
  )
install(FILES ${HEADERS} DESTINATION include/gula/net)

if(GULA_BUILD_EXAMPLES)
  add_subdirectory(tests)
endif()

