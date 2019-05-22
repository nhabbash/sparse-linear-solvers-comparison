function main(inputfile)

    load(inputfile);
    
    [rows, columns] = size(Problem.A);

    xe = ones(columns, 1);
    b = Problem.A * xe;
    
    tic;
    x = Problem.A \ b;
    time = toc;

    error = norm(x - xe) / norm(xe);
    
    % Logging
    
    platform = "Other";
    
    if isunix
        platform = "Linux";
    elseif ispc
        platform = "Windows";
    end

    date = datestr(now,'dd-mm-yyyy HH:MM:SS');
    timestamp = datestr(now,'ddmmyyyy-HH:MM:SS');
    
    args = strsplit(inputfile, "/");
    mat_name = args(end);
    log_path = "../log/";
    logfile = mat_name + "-matlab-" + platform + "-" + timestamp + ".log";
    file = fopen(log_path + logfile, 'a');
    
    
    fprintf(file,'Date, %s \n', date);
    fprintf(file,'Factorization + Resolution time, %f \n', time);
    fprintf(file,'Relative error, %e\n\n', error);
    fclose(file);
    %disp(logfile);
end