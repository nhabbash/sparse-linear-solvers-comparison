
fileID = fopen('matrices_stats.csv','w');
fprintf(fileID,'%s\t%s\t%s\n','matrix','size','nonzeros');

path = './matrices/';
files = dir(strcat(path, '*.mat'));

for i=1:length(files)
    matrix_name = files(i).name;
    matrix_path = strcat(path, matrix_name);
    load(matrix_path);
    matrix = Problem.A;
    [rows, cols] = size(matrix);
    nonzeros = nnz(matrix);
    fprintf(fileID, '%s\t%.0f\t%.0f\n', matrix_name, rows, nonzeros);
end