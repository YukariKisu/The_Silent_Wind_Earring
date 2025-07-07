@echo off
nrfjprog -f nrf52 --eraseall
nrfjprog -f nrf52 --program _build\nrf52832_xxaa.hex --verify
nrfjprog -f nrf52 --reset
pause

