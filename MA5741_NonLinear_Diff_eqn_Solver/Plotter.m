clear; clc;
rawdata = readmatrix('GridPoints_Qn3 (2).csv');
rawdata2 = readmatrix('GridPoints_Qn3 (2).csv');


x1 = reshape(rawdata(:,1),[],11);       % Reshape the column matrix into 51 columns
y1 = reshape(rawdata(:,2),[],11);
z1 = reshape(rawdata(:,3),[],11);
surf(x1,y1,z1)
