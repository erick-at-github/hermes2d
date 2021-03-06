// K (van Genuchten).
double K(double h)
{
  if (h < 0) return (1-pow(-ALPHA*h,M*N)*pow((1+pow(-ALPHA*h,N)),-M))*
                    (1-pow(-ALPHA*h,M*N)*pow((1+pow(-ALPHA*h,N)),-M))/   
	            (pow(1 + pow(-ALPHA*h,N),M/2));
  else return K_S;    
}

// dK/dh (van Genuchten).
double dKdh(double h)
{
  if (h < 0) return (ALPHA*pow(-(ALPHA*h),-1 + N)*pow(1 + pow(-(ALPHA*h),N),-1 - M/2.)*
	      pow(1 - pow(-(ALPHA*h),M*N)/pow(1 + pow(-(ALPHA*h),N),M),
	      2)*M*N)/2. + (2*(1 - 
	      pow(-(ALPHA*h),M*N)/pow(1 + pow(-(ALPHA*h),N),M))*
	      (-(ALPHA*pow(-(ALPHA*h),-1 + N + M*N)*
	      pow(1 + pow(-(ALPHA*h),N),-1 - M)*M*N) + 
	      (ALPHA*pow(-(ALPHA*h),-1 + M*N)*M*N)/
	      pow(1 + pow(-(ALPHA*h),N),M)))/
	      pow(1 + pow(-(ALPHA*h),N),M/2.) ;
  else return 0;
}

// ddK/dhh (van Genuchten).
double ddKdhh(double h)
{
  if (h < 0) return -(pow(ALPHA,2)*pow(-(ALPHA*h),-2 + N)*
	      pow(1 + pow(-(ALPHA*h),N),-1 - M/2.)*
	      pow(1 - pow(-(ALPHA*h),M*N)/pow(1 + pow(-(ALPHA*h),N),M),
	      2)*M*(-1 + N)*N)/2. - 
	      (pow(ALPHA,2)*pow(-(ALPHA*h),-2 + 2*N)*
	      pow(1 + pow(-(ALPHA*h),N),-2 - M/2.)*
	      pow(1 - pow(-(ALPHA*h),M*N)/pow(1 + pow(-(ALPHA*h),N),M),
	      2)*(-1 - M/2.)*M*pow(N,2))/2. + 
	      2*ALPHA*pow(-(ALPHA*h),-1 + N)*
	      pow(1 + pow(-(ALPHA*h),N),-1 - M/2.)*
	      (1 - pow(-(ALPHA*h),M*N)/pow(1 + pow(-(ALPHA*h),N),M))*M*N*
	      (-(ALPHA*pow(-(ALPHA*h),-1 + N + M*N)*
	      pow(1 + pow(-(ALPHA*h),N),-1 - M)*M*N) + 
	      (ALPHA*pow(-(ALPHA*h),-1 + M*N)*M*N)/
	      pow(1 + pow(-(ALPHA*h),N),M)) + 
	      (2*pow(-(ALPHA*pow(-(ALPHA*h),-1 + N + M*N)*
	      pow(1 + pow(-(ALPHA*h),N),-1 - M)*M*N) + 
	      (ALPHA*pow(-(ALPHA*h),-1 + M*N)*M*N)/
	      pow(1 + pow(-(ALPHA*h),N),M),2))/
	      pow(1 + pow(-(ALPHA*h),N),M/2.) + 
	      (2*(1 - pow(-(ALPHA*h),M*N)/pow(1 + pow(-(ALPHA*h),N),M))*
	      (pow(ALPHA,2)*pow(-(ALPHA*h),-2 + 2*N + M*N)*
	      pow(1 + pow(-(ALPHA*h),N),-2 - M)*(-1 - M)*M*pow(N,2)
	      + pow(ALPHA,2)*pow(-(ALPHA*h),-2 + N + M*N)*
	      pow(1 + pow(-(ALPHA*h),N),-1 - M)*pow(M,2)*pow(N,2)
	      - (pow(ALPHA,2)*pow(-(ALPHA*h),-2 + M*N)*M*N*(-1 + M*N))/
	      pow(1 + pow(-(ALPHA*h),N),M) + 
	      pow(ALPHA,2)*pow(-(ALPHA*h),-2 + N + M*N)*
	      pow(1 + pow(-(ALPHA*h),N),-1 - M)*M*N*(-1 + N + M*N)))/
	      pow(1 + pow(-(ALPHA*h),N),M/2.) ;
  else return 0;
}

// C (van Genuchten).
double C(double h)
{
  if (h < 0) return ALPHA*pow(-(ALPHA*h),-1 + N)*pow(1 + pow(-(ALPHA*h),N),-1 - M)*M*N*(THETA_S - THETA_R) + 
	    (THETA_S-THETA_R)/pow(1+pow(-ALPHA*h,N),M)/THETA_S*STORATIVITY;
  else return STORATIVITY;    
}

// dC/dh (van Genuchten).
double dCdh(double h)
{
  if (h < 0) return (-(pow(ALPHA,2)*pow(-(ALPHA*h),-2 + N)*
	      pow(1 + pow(-(ALPHA*h),N),-1 - M)*M*(-1 + N)*N) - 
	      pow(ALPHA,2)*pow(-(ALPHA*h),-2 + 2*N)*
	      pow(1 + pow(-(ALPHA*h),N),-2 - M)*(-1 - M)*M*pow(N,2) + 
	      ALPHA*pow(-(ALPHA*h),-1 + N)*pow(1 + pow(-(ALPHA*h),N),-1 
              - M)*M*N/THETA_S*STORATIVITY)*(THETA_S - THETA_R) ;
  else return 0;    
}
