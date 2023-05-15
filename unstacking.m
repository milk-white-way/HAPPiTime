function index = unstacking(counter, index, param)
    index.ustack_y(counter) = rem(index.stack(counter), param.N);
    if index.ustack_y(counter) == 0
        index.ustack_y(counter) = param.N;
    end
    index.ustack_x(counter) = ( index.stack(counter) ...
        - index.ustack_y(counter) )/param.N + 1;
end