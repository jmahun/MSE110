%%
clc;
clear;
close all;

% creating matrix from image, read csv as table 

noisy_Image = readtable('C:\Users\bkj1\Downloads\small-2.csv');

% extracting "Var4" -> column with sensor values

middleMatrixRow = noisy_Image(:, "Var4");

% plot column

plot(middleMatrixRow.Var4);

% window size chosen from trial and error
window_size=5.6;

% loop through row, from 1 to length(middleMatrixRow.Var4) - window_size-1, to hold moving average values

for i=1:length(middleMatrixRow.Var4)-(window_size-1)
    % create new array called middleMatrixRowAvg to hold moving averages
     middleMatrixRowAvg(i)=sum(middleMatrixRow.Var4(i:i+(window_size-1)))/window_size;

% terminate for loop

end

% retain current plot from middleMatrixRow, while adding new plots from middleMatrixRowAvg

hold on
plot(middleMatrixRowAvg)

% loop through average array, to calculate moving average slope 
% formula: abs(averagearray(i+1)-averagearray(i)) -> time interval: 1 (increments of i)

for i=1:length(middleMatrixRowAvg)-1
    middleMatrixRowAvg(i) = abs(middleMatrixRowAvg(i+1) - middleMatrixRowAvg(i));
end

% display figure 1

figure;

% plot derivative array

plot(middleMatrixRowAvg);
hold on 

% finding peaks

[pks,locs] = findpeaks(middleMatrixRowAvg,'MinPeakHeight',0.27,'MinPeakDistance',4.8);
plot(locs,pks,'or');

%  finding width of bar code blocks

widths = (locs(2:end)-locs(1:end-1));

widths = floor( widths/min(widths));

% width helper to normalize values(values should always be 1 or 3)

for i = 1:length(widths)
% if width less than 1, width = 1
  if widths(i) < 1
    widths(i) = 1;
% if width greater than 3, width = 3
  elseif widths(i) > 3
    widths(i) = 3;
% if width = 2, make 3 instead
  elseif widths(i) == 2
    widths(i) = 3;
% if width is between 2 and 1, width = 1
    if(widths(i) < 2*min(widths))
      widths(i) = 1;
    end
  end
end

%**************Patern Recognition Using Lookup Table *
LOOKUPTABLE =    [
311113113; %A
113113113; %B
313113111; %C
111133113; %D
311133111; %E
113133111; %F
111113313; %G
311113311; %H
113113311; %I
111133311; %J
311111133; %K
113111133; %L
313111131; %M
111131133; %N
311131131; %O
113131131; %P
111111333; %Q
311111331; %R
113111331; %S
111131331; %T
331111113; %U
133111113; %V
333111111; %W
131131113; %X
331131111; %Y
133131111]; %Z

% match widths to lookup table       
           
CODE = str2num(strrep(num2str(widths), ' ', ''));

           
  coor = find(LOOKUPTABLE == CODE);
  Letter = char(64+coor)
