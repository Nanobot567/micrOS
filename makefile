# ----------------------------
# Makefile Options
# ----------------------------

NAME = MICROS
ICON = icon.png
DESCRIPTION = "micrOS v1.0a"
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
