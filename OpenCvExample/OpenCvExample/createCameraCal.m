function createCameraCal()

screen_width_cm = 130.7;
screen_width_px = 3500;

screen_height_cm = 74.7;
screen_height_px = 2000;


% Load calibration data from all three left camera captures.
[screenPxRow100cmDist,screenPxCol100cmDist,cameraPxRow100cmDist,cameraPxCol100cmDist] = textread('calDataLeft100cm.txt',"%d, %d, %d, %d");

[screenPxRow60cmDist,screenPxCol60cmDist,cameraPxRow60cmDist,cameraPxCol60cmDist] = textread('calDataLeft60cm.txt',"%d, %d, %d, %d");

[screenPxRow30cmDist,screenPxCol30cmDist,cameraPxRow30cmDist,cameraPxCol30cmDist] = textread('calDataLeft30cm.txt',"%d, %d, %d, %d");


% Find points that exist in all three calibration matrices

rmsErrorMin = 1000000;

iEntryMinErr = -1;

for iEntry = 1:length(screenPxRow30cmDist)

  screenPxRow = screenPxRow30cmDist(iEntry);

  screenPxCol = screenPxCol30cmDist(iEntry);

  iMatch100cm = find((screenPxRow100cmDist == screenPxRow) & (screenPxCol100cmDist == screenPxCol));

  iMatch60cm = find((screenPxRow60cmDist == screenPxRow) & (screenPxCol60cmDist == screenPxCol));

  if (!isempty(iMatch100cm) && !isempty(iMatch60cm))

    cameraPxRowDiff100cm = cameraPxRow100cmDist(iMatch100cm) - cameraPxRow30cmDist(iEntry);

    cameraPxColDiff100cm = cameraPxCol100cmDist(iMatch100cm) - cameraPxCol30cmDist(iEntry);

    cameraPxRmsErr100cm = sqrt(cameraPxRowDiff100cm^2 + cameraPxColDiff100cm^2);

    cameraPxRowDiff60cm = cameraPxRow60cmDist(iMatch60cm) - cameraPxRow30cmDist(iEntry);

    cameraPxColDiff60cm = cameraPxCol60cmDist(iMatch60cm) - cameraPxCol30cmDist(iEntry);

    cameraPxRmsErr60cm = sqrt(cameraPxRowDiff60cm^2 + cameraPxColDiff60cm^2);

    if max(cameraPxRmsErr100cm, cameraPxRmsErr60cm) < rmsErrorMin

      rmsErrorMin = max(cameraPxRmsErr100cm, cameraPxRmsErr60cm);

      iEntryMinErr = iEntry;

    endif

  endif






end


keyboard;


endfunction


