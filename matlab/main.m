function main(inputfile)

    load(inputfile);
    
    [rows, columns] = size(Problem.A);

    xe = ones(columns, 1);
    b = Problem.A * xe;
    
    tic;
    x = Problem.A \ b;
    time = toc;

    error = norm(x - xe) / norm(xe);
    
    % Writing logfile
    
    platform = "Other";
    
    if isunix
        platform = "Linux";
    elseif ispc
        platform = "Windows";
    end

    date = datestr(now,'dd-mm-yyyy HH:MM:SS');    

    args = strsplit(inputfile, "/");
    mat_name = args(end);
    name = split(mat_name, ".");
    name = string(name(1));

    data_file = "../data/data.csv";
    file = fopen(data_file, 'a');
    
    % ["date", "platform", "name", "library", "factorization time", "resolution time", "relative error", "physical memory", "virtual memory"])
    fprintf(file,'%s, ', date);
    fprintf(file,'%s, ', platform);
    fprintf(file,'%s, ', name);
    fprintf(file,'matlab, ');
    fprintf(file,'%f, ', time);
    fprintf(file,'null, ');
    fprintf(file,'%e, ', error);
    fclose(file);
end