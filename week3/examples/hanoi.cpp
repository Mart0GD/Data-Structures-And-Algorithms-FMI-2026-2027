#include <iostream>
#include <stack>

#define towers_of_hanoi(disks) toh(disks, 1, 3);

void toh(int disks, int from, int to)
{
    if(disks > 0)
    {	
	// вземаме останалата колона 
	int other = 6 - (to + from);

	// мърдаме всички дискове без един на междинната колона
	toh(disks - 1, from, other);

	// мръднали сме останалите дискове
	std::cout << from << "->" << to << std::endl;

	// свеждаме проблема обратно, но за n - 1 диска
	toh(disks - 1, other, to);
    }
}    

void toh_sim(int disks)
{
    typedef struct context
    {
	// ---- Context ----
	int disks;
	int from;
	int to;

	
	/*
	*    ---- Stage of completion ----
	*
	*    0 -> before first call
	*    1 -> after first call
	*    2 -> after second call (the end of the call
	*/
	int stage;
    } context;

    std::stack<context> program_stack;

    // start condition
    program_stack.push({3,1,3,0});

    while(!program_stack.empty())
    {
	context& ctx = program_stack.top();

	int disks = ctx.disks;
	int from  = ctx.from;
	int to    = ctx.to; 

	if(disks == 0)
	{
	    program_stack.pop();
	    continue;
	}
	if(ctx.stage == 0)
	{
	    ctx.stage++;
	    int other = 6 - (from + to);
            context new_call = {disks - 1, from, other};	    
	    
	    program_stack.push(new_call);
	}
	else if (ctx.stage == 1)
	{
	    ctx.stage++;
	    
	    std::cout << from << "->" << to << '\n';
	    context new_call = {disks - 1, 6 - (from + to), to};
	    
	    program_stack.push(new_call);	   
	}
	else if (ctx.stage == 2)
	{
	    program_stack.pop();
	}
    }
}

int main(void)
{
    // towers_of_hanoi(3);
    toh_sim(3);
    return 0;
}    
