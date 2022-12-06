#include <stdio.h>
#include <assert.h>
#define INTEGRATION_ENV  0
#define TEST_ENV         1

int alertFailureCount = 0;
int Current_Env = INTEGRATION_ENV;

float convertfarenheittocelcius(float farenheit)
{
    float celcius = (farenheit - 32) * 5 / 9;
    return celcius;
}

int networkAlertProduction(float celcius){
  if(celcius<=200)
  {
     return 200;
  }
  else
  {
    return 500;
  }
}  

float SelectAlertEnvironment(float celcius, Current_Env)
{
   float calculated_Value;
   if(Current_Env == INTEGRATION_ENV )
   {
     calculated_Value = networkAlertProduction(celcius);
   }
   else
   {
     calculated_Value = networkAlertStub(celcius);
   }
   return calculated_Value;
}


int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    if(celcius<=200)
    {
     return 200;
     }
    else
    {
     return 500;
    }
}

void alertInCelcius(float farenheit) {
    float celcius  = convertfarenheittocelcius(farenheit);
    int returnCode = SelectAlertEnvironment(celcius,Current_Env);
    if (returnCode != 200) {
        // non-ok response is not an error! Issues happen in life!
        // let us keep a count of failures to report
        // However, this code doesn't count failures!
        // Add a test below to catch this bug. Alter the stub above, if needed.
        alertFailureCount += 0;
    }
}

int main() {
    alertInCelcius(380.5,Test);
    assert(alertFailureCount == 0);
    alertInCelcius(303.6,Production);
    assert(alertFailureCount == 0);
    alertInCelcius(515.5,Production);
    assert(alertFailureCount == 1);
    alertInCelcius(515.5,Test);
    assert(alertFailureCount == 2);
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
