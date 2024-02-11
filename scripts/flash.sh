#!/bin/bash

export ESPPORT="/dev/ttyUSB0"

virtualenv venv
source venv/bin/activate
python -m pip install --upgrade pip
python -m pip install -r $IDF_PATH/requirements.txt

cd build/
make flash
