 


set RELEASE_DIR=QuickLib-%date:~0,4%%date:~5,2%%date:~8,2%


del .\dist\*.* /q

rem python.exe setup.py py2exe --includes sip,CTPMarket,CTPMarketType,PyCTPTrader,PyCTPType
python.exe setup.py py2exe --includes sip

copy QuickLibMD.ini .\dist\
copy QuickLibTD.ini .\dist\
copy config.ini  .\dist\
copy setting.xls .\dist\
copy version.txt .\dist\
copy start.bat   .\dist\

copy QuickLibAShareMD.dll  .\dist\
copy QuickLibAShareTD.dll  .\dist\

copy thostmduserapi.dll   .\dist\

copy thosttraderapi.dll   .\dist\

copy TradeTime.ini   .\dist\

copy TradeRecord.txt  .\dist\

copy Instrument.ini  .\dist\


mkdir %RELEASE_DIR%
del .\%RELEASE_DIR%\*.* /q
xcopy .\dist\*.* %RELEASE_DIR%
