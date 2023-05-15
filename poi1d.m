%% PARAMETERS
N = 101;

x = linspace(0, 1, N); x = x';
h = diff(x); h = h(1);

%% ASEMBLY
A = zeros(N, N);
b = zeros(N, 1);

for ii = 2:N-1
    A(ii, ii-1) = 1;
    A(ii, ii)   = -2;
    A(ii, ii+1) = 1;
    
    b(ii) = h*h;
end

A(1, 1) = 1;
A(1, 2:end) = 0;

A(N, N) = 1;
A(N, 1:end-1) = 0;

%% SOLVE
U = A\b;

%% PLOT
y = linspace(0, 1, 1e4); y = y';
for ii = 1:length(y)
    USOL(ii) = 0.5*y(ii)^2 - 0.5*y(ii);
end

figure()
plot(x, U, 'o'); hold on
plot(y, USOL);
grid on;