extern "C" const char* GetName()
{
    return "Merge";
}

extern "C" int Compute(int param1, int param2)
{
    return param1 + param2;
}
