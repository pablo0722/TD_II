fclose(srl);
delete(srl);
clear srl

open_uarts = instrfind;

if ~(isempty(open_uarts))
    fclose (open_uarts);
end