"C:\Program Files\Parsec\parsecd.exe"

timeout /t 1
tasklist /fi "imagename eq parsecd.exe" | find /i /n "parsecd.exe" >nul

if errorlevel 1 (
    goto :start
)
