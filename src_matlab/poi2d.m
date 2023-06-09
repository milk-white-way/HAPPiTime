%% START
clearvars; format long;

%% PARAMETER FIELD
N = 201;
x = linspace(0, 1, N); x = x'; h = diff(x); h = h(1);

param.x = x;
param.y = x; 
param.h = h;
param.N = N;

%% VARIABLE FIELD
% Poisson variables
poisson.lhs = zeros(N*N, N*N);
poisson.rhs = zeros(N*N, 1);
poisson.vec = zeros(N*N, 1);
poisson.mat = zeros(N, N);

stack = linspace(1, N*N, N*N);

% Indices
index.stack = stack';

index.north = zeros(N*N, 1);
index.south = zeros(N*N, 1);

index.east = zeros(N*N, 1);
index.west = zeros(N*N, 1);

index.centroid = zeros(N*N, 1);

index.ustack_x = zeros(N*N, 1);
index.ustack_y = zeros(N*N, 1);

clearvars N x h stack;
%% ASEMBLY
counter = 0;
while 1
    counter = counter + 1;
    if counter > index.stack(end)
        break
    end
    index = unstacking(counter, index, param);

    if (index.ustack_x(counter) >= 2 && ...
            index.ustack_x(counter) <= param.N -1 && ...
            index.ustack_y(counter) >= 2 && ...
            index.ustack_y(counter) <= param.N -1)
        
        index.centroid(counter) = stacking(index.ustack_x(counter), index.ustack_y(counter), param);

        index.north(counter) = stacking(index.ustack_x(counter), index.ustack_y(counter)+1, param);
        index.south(counter) = stacking(index.ustack_x(counter), index.ustack_y(counter)-1, param);

        index.east(counter) = stacking(index.ustack_x(counter)-1, index.ustack_y(counter), param);
        index.west(counter) = stacking(index.ustack_x(counter)+1, index.ustack_y(counter), param);

        poisson.lhs(index.stack(counter), index.centroid(counter)) = -2/(param.h^2) - 2/(param.h^2);
        poisson.lhs(index.stack(counter), index.north(counter)) = 1/param.h^2;
        poisson.lhs(index.stack(counter), index.south(counter)) = 1/param.h^2;
        poisson.lhs(index.stack(counter), index.east(counter)) = 1/param.h^2;
        poisson.lhs(index.stack(counter), index.west(counter)) = 1/param.h^2;

        poisson.rhs(index.stack(counter)) = 1;
    else
        poisson.lhs(index.stack(counter), index.stack(counter)) = 1;
        poisson.rhs(index.stack(counter)) = 0;

    end

end

%% SOLVE FOR SOLUTION
poisson.vec = poisson.lhs\poisson.rhs;

%% UNSTACK THE SOLUTION
counter = 0;
while 1
    counter = counter + 1;
    if counter > index.stack(end)
        break
    end
    poisson.mat(index.ustack_x(counter), index.ustack_y(counter)) = poisson.vec(counter);
end

figure(); 
subplot(2,1,1);
    mesh(poisson.mat);
subplot(2,1,2);
    plot(poisson.vec);