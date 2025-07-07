$NRFJPROG = "C:\Program Files\Nordic Semiconductor\nrf-command-line-tools\bin\nrfjprog.exe"
& "$NRFJPROG" -f nrf52 --program _build\nrf52832_xxaa.hex --sectorerase --verify
& "$NRFJPROG" -f nrf52 --reset
