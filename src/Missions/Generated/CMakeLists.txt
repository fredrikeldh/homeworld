ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/foo.c
   COMMAND ${CMAKE_COMMAND} copy ${CMAKE_CURRENT_SOURCE_DIR}/bar.c ${CMAKE_CURRENT_BINARY_DIR}/foo.c
   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/bar.c
   )
 ADD_EXECUTABLE(foo foo.c)


# Kinda weak dependency on kas2c (doesn't build it if it doesn't exist), but
# we should be fine as long as it's built first.
%.c %.h %.func.c: %.kp $(top_builddir)/tools/kas2c/kas2c$(EXEEXT)
	$(top_builddir)/tools/kas2c/kas2c$(EXEEXT) $< $(basename $@).c $(basename $@).h $(basename $@).func.c

# Single-player missions (note the "-x c" option to force C
# preprocessing...don't know if this is very portable)
Mission%.kp: $(top_builddir)/src/Missions/SinglePlayer/Mission%.kas
	$(CPP) -x c $(INCLUDES) $< > $@

# Tutorials (again, uses "-x c" to force C preprocessing)
Tutorial%.kp: $(top_builddir)/src/Missions/Tutorials/Tutorial%.kas
	$(CPP) -x c $(INCLUDES) $< > $@

add_library(
libhw_Generated
Mission01.c Mission01.func.c Mission02.c Mission02.func.c Mission02.h Mission03.c Mission03.func.c Mission04.c Mission04.func.c Mission05.c Mission05.func.c Mission05_OEM.c Mission05_OEM.func.c Mission06.c Mission06.func.c Mission07.c Mission07.func.c Mission08.c Mission08.func.c Mission09.c Mission09.func.c Mission10.c Mission10.func.c Mission11.c Mission11.func.c Mission12.c Mission12.func.c Mission13.c Mission13.func.c Mission14.c Mission14.func.c Mission15.c Mission15.func.c Mission16.c Mission16.func.c Tutorial1.c Tutorial1.func.c
)
