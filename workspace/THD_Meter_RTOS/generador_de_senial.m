clear all;
close all;
clc;

text = [];
aux = [];

for i=1:4
    for j=1:8
        for k=1:32
            aux = [aux 'FFFFFFFF' ' '];
        end
        
        text = [text ; aux];
        aux = [];
    end
    
    for j=1:8
        for k=1:32
            aux = [aux '00000000' ' '];
        end
        
        text = [text ; aux];
        aux = [];
    end
end

text