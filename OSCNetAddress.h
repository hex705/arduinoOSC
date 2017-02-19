//=============================================================================

class NetAddress {
    

 protected:
	
    IPAddress destinationIP;
    int       destinationPort; 
    
public:

    
    NetAddress(void);
    void set (IPAddress, int);
    IPAddress getIP();
    int getPort();

    
};

