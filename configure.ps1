#[CMDLETBINDING()]

# Download SFML library zipped archive
echo "DOWNLOAD SFML"
$Url = "https://github.com/SFML/SFML/releases/download/2.5.1/SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit.zip"
$Arch = "$pwd/SFML-2.5.1.zip"
echo "Download file from"
echo "	$Url"
echo "to"
echo "	$Arch"
$WebClient = New-Object System.Net.WebClient
$WebClient.DownloadFile($url,$Arch)

# Unzip SFML archive
echo "UNZIP SFML"
echo "unzip file $Arch"
Expand-Archive $Arch -DestinationPath ./
