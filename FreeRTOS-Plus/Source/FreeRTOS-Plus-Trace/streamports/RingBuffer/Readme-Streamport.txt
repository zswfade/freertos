Tracealyzer Stream Port for Ring Buffer
-------------------------------------------------

This directory contains a "stream port" for the Tracealyzer recorder library,
i.e., the specific code needed to use a particular interface for streaming a
Tracealyzer RTOS trace. The stream port is defined by a set of macros in
trcStreamPort.h, found in the "include" directory.

This particular stream port is for streaming to a ring buffer.

To use this stream port, make sure that include/trcStreamPort.h is found
by the compiler (i.e., add this folder to your project's include paths) and
add all included source files to your build. Make sure no other versions of
trcStreamPort.h are included by mistake!

See also http://percepio.com/2016/10/05/rtos-tracing.

Percepio AB
www.percepio.com