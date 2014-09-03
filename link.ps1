$shell = New-Object -ComObject WScript.Shell;
$desktop = [System.Environment]::GetFolderPath('Desktop');
$shortcut = $shell.CreateShortcut("$desktop\QFramer.lnk");
$shortcut.TargetPath = "E:\Program Files\QFramer\QFramer.exe";
$shortcut.IconLocation = "E:\Program Files\QFramer\QFramer.exe,0";
$shortcut.Save();