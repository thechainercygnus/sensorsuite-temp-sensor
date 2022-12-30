# Temp Sensor

This is my simple ESP32 WiFi temperature sensor for my [SensorSuite](https://github.com/thechainercygnus/sensorsuite-server).

On Windows after cloning repository, dot source the Settings script:
`. .\Set-DeviceSettings.ps1`

Then create the custom configurations for each kit:

```powershell
    $DeviceSettings = @{
        SensorName = "SENSOR NAME"
        SSID = "SSID NAME"
        Passphrase = "WIFI PASSPHRASE"
        Endpoint = "http://sensorsuite.DOMAIN.TLD/VERSION/temperature/"
        DHT11 = $false # Omit or Set to $true to use DHT11 instead of DHT22
        DHTPin = 4 # Omit or Set to Digital GPIO Pin used for wiring
        SleepDelay = 60000 # Omit or Set to Milliseconds to Sleep between Updates
}
Set-DeviceSettings @DeviceSettings
```

**NOTE:** Ensure the trailing slash is included in the endpoint uri. This will prevent 307 Redirect responses to every request and a failure to record readings.
