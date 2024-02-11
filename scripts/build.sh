#!/bin/bash

virtualenv venv
source venv/bin/activate

python -m pip install -r $IDF_PATH/requirements.txt
mkdir -p build/
cd build/
cmake .. -G "Unix Makefiles"
make
