function Set-DeviceSettings {
    [CmdletBinding()]
    param (
        [Parameter(Mandatory=$true, Position=0)]
        [string]
        $SensorName,

        [Parameter(Mandatory=$true, Position=1)]
        [string]
        $SSID,

        [Parameter(Mandatory=$true, Position=2)]
        [string]
        $Passphrase,

        [Parameter(Mandatory=$true, Position=3)]
        [string]
        $Endpoint,

        [Parameter(Mandatory=$false, Position=4)]
        [int]
        $DHTPin,

        [Parameter(Mandatory=$false, Position=5)]
        [int]
        $SleepDelay,

        [Parameter()]
        [switch]
        $DHT11
    )
    $inoFileContent = Get-Content "temp_sensor.ino"
    $updatedContents = $inoFileContent.Replace("ENTER_SENSOR_IDENTIFIER", $SensorName).Replace("ENTER_SSID",$SSID).Replace("ENTER_PASSPHRASE",$Passphrase).Replace("ENTER_SENSORSUITESERVER_ENDPOINT_URI",$Endpoint)
    $FileName = "temp_sensor_$SensorName.ino"
    if ($DHT11) {
        $updatedContents = $updatedContents.Replace("DHT22", "DHT11")
    }
    if ($DHTPin) {
        $updatedContents = $updatedContents.Replace("#define DHTPIN 4","#define DHTPIN $DHTPin")
    }
    if ($SleepDelay) {
        $updatedContents = $updatedContents.Replace("unsigned long timerDelay = 60000;","unsigned long timerDelay = $SleepDelay;")
    }
    New-Item $FileName
    Set-Content $FileName $updatedContents
}
