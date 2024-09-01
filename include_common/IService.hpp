namespace TestTask
{
    class IService
    {
    public:
        virtual ~IService() = default;
        virtual void run() = 0;
        virtual void stop() = 0;
        virtual bool isRunning() {return mIsRunning;}

    protected:
    bool mIsRunning{false};
    };
} //!TestTask
