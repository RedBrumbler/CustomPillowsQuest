Param(
    [String]$qmodname="",
    [Parameter(Mandatory=$false)]
    [Switch]$clean
)

if ($qmodName -eq "")
{
    echo "Give a proper qmod name and try again"
    exit
}
$mod = "./mod.json"
$modJson = Get-Content $mod -Raw | ConvertFrom-Json

$filelist = @($mod)

$cover = "./" + $modJson.coverImage
$fileList = @($mod)

if ((-not ($cover -eq "./")) -and (Test-Path $cover))
{
    $fileList += ,$cover
}

foreach ($mod in $modJson.modFiles)
{
    $path = "./build/" + $mod
    if (-not (Test-Path $path))
    {
        $path = "./extern/libs/" + $mod
    }
    $filelist += $path
}

foreach ($lib in $modJson.libraryFiles)
{
    $path = "./build/" + $lib
    if (-not (Test-Path $path))
    {
        $path = "./extern/libs/" + $mod
    }
    $filelist += $path
}

$ignoredFileSubStrings = @("ExtraPillows", "template", "Piles.png")
if (Test-Path "./ExtraFiles")
{
    $extraFiles = @()
    $extraEntries = Get-ChildItem ./ExtraFiles/* -Recurse

    foreach ($entry in $extraEntries)
    {
        $mode = $entry | Select -Expand Mode
        if ($mode.Contains("d"))
        {
            continue
        }

        # if not a dir
        if (-not $entry.Directory.Name.Contains("ExtraFiles"))
        {
            $dir = $entry.Directory
            $folderPath = $dir.Name + "/" + $entry.Name
            while (($dir.Directory) -and (-not $dir.Directory.Name.Contains("ExtraFiles")))
            {
                $folderPath = $dir.Directory.Name + "/" + $folderPath
            }

            $found = $false
            foreach ($ignore in $ignoredFileSubStrings) {
                if ($folderPath.Contains($ignore)) {
                    $found = $true
                    break
                }
            }

            if ($found) {
                continue
            }
            $extraFiles += ,$folderPath
        }
        else
        {
            $found = $false
            foreach ($ignore in $ignoredFileSubStrings) {
                if ($entry.Name.Contains($ignore)) {
                    $found = $true
                    break
                }
            }

            if ($found) {
                continue
            }
            $extraFiles += ,$entry.Name
        }
    }

    foreach ($file in $extraFiles)
    {
        $path = "./ExtraFiles/" + $file
        $filelist += ,$path
    }
}
else
{
    echo "No ExtraFiles Directory Found"
}

$zip = $qmodName + ".zip"
$qmod = $qmodName + ".qmod"

if ($clean.IsPresent) {
    echo "Making Clean Qmod"
}

if ((-not ($clean.IsPresent)) -and (Test-Path $qmod))
{
    Move-Item $qmod $zip -Force
}

Compress-Archive -Path $filelist -DestinationPath $zip -Update
Move-Item $zip $qmod -Force
