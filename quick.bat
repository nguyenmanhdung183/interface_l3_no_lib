echo off
setlocal


set RUN_PATH=src_code_no_lib

REM set RUN_PATH=src_code

REM run 1.prepare_struct.py
python ./%RUN_PATH%/_1_prepare_struct.py
if %ERRORLEVEL% neq 0 (
    echo Error occurred in _1_prepare_struct.py, stopping.
    exit /b 1
)
REM run 2.make_excel.py
python ./%RUN_PATH%/_2_make_excel.py
if %ERRORLEVEL% neq 0 (
    echo Error occurred in _2_make_excel.py, stopping.
    exit /b 1
)
REM run 3_generate.py
python ./%RUN_PATH%/_3_generate.py
if %ERRORLEVEL% neq 0 (
    echo Error occurred in _3_generate.py, stopping.
    exit /b 1
)
REM run 4_format_merge.py
python ./%RUN_PATH%/_4_format_merge.py
if %ERRORLEVEL% neq 0 (
    echo Error occurred in _4_format_merge.py, stopping.
    exit /b 1
)

endlocal