#!/usr/bin/python
# GPL version 2 or later

import sys

from iotop.ui import main

try:
    main()
except KeyboardInterrupt:
    pass
sys.exit(0)
