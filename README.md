IoT Controller
==============

Project configuration
---------------------

Install ESP toolchain and SDK
```bash
./setup.sh
```

Activate Python virtualenv and install required packages. Python 3 is required:
```bash
virtualenv venv
source venv/bin/activate
python -m pip install  -r $IDF_PATH/requirements.txt
```

**IMPORTANT:** Python virtualenv MUST be activated before using `make`


Development
-----------

Activate Python virtualenv with `source venv/bin/activate`

Compile project: `make all`

Compile and flash: `make flash`

Viewing serial output: `make monitor`

Build just the app: `make app`

Flash just the app: `make app-flash` - will automatically rebuild the app if it needs it

Speed up build with compiling multiple files in parallel: `make -jN app-flash` - where N is the number of parallel make processes to run (generally N should be equal to or one more than the number of CPU cores in your system.)

Erase the entire flash: `make erase_flash`

Make targets could be combined in one run
