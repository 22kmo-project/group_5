#include "myurl.h"

myUrl::myUrl()
{

}

QString myUrl::getBaseUrl()
{
    return base_url;
}

QString myUrl::base_url{
    "http://localhost:3000"
};
