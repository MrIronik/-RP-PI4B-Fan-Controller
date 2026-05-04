# Basic RP PI 4B fan driver

Driveing simple fan with transistor form GPIO.


# Stress comands

### Install Stess framework

```bash
sudo apt install stress-ng
```

### Use it

```bash
stress-ng --cpu 4 --timeout 60s
```

--cpu -> number of cores to be used (max 4 in rp pi 4b)
