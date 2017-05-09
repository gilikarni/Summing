#pragma once

/*
    File description:
     This file contain the API for parsing the input traces
*/

#ifndef PARSER_H
#define PARSER_H

/* Includes: */
#include <string>

using std::string;

/*
    Class name: Time

    Description: 
     The class contains the time of a package
     that was deliverd
 */
class Time
{
    /* The hour that the package was recieved */
    uint8_t hour;
    /* The minute that the package was recieved */
    uint8_t minute;
    /* The seconf that the package was recieved */
    double second;
    /* A string describing the time of the deliver */
    string timeStr;

public:

    /* Constructor: */

    Time(const string& time);

    /* API: */

    /* 
        Function name: Time::getHour
        
        Description: 
         An API to get the hour of the deliver

        Parameters:
         None

        Return values:
         The hour of the deliver
     */
    uint8_t getHour() const;

    /*
        Function name: Time::getMinute

        Description: 
         An API to get the minute of the deliver

        Parameters:
         None

        Return values:
         The minute of the deliver
    */
    uint8_t getMinute() const;

    /*
        Function name: Time::getSecond

        Description: 
         An API to get the second of the deliver

        Parameters:
         None

        Return values:
         The second of the deliver
    */
    double getSecond() const;

    /*
        Function name: Time::getTimeAsString

        Description: 
         An API to get a string describing the time of the deliver

        Parameters:
         None

        Return values:
         A string describing the time of the deliver
    */
    string getTimeAsString() const;
};

/*
    Class name: Package

    Description: 
     This class identifies a package that was delivered
*/
class Package
{
    /* The time of the deliver */
    Time time;
    /* The ip from whom the package */
    string ip;
    /* The port from whom the package was sent */
    uint16_t port;
    /* The size of the package */
    uint64_t size;

public:

    /* Constructor: */

    Package(string trace);

    /* API: */

    /*
        Function name: Package::getHour

        Description: 
         An API to get the hour of the deliver

        Parameters:
         None

        Return values:
         The hour of the deliver
    */
    uint8_t getHour() const;

    /*
        Function name: Package::getMinute

        Description: 
         An API to get the minute of the deliver

        Parameters:
         None

        Return values:
         The minute of the deliver
    */
    uint8_t getMinute() const;

    /*
        Function name: Package::getSecond

        Description: 
         An API to get the second of the deliver

        Parameters:
         None

        Return values:
         The second of the deliver
    */
    double getSecond() const;

    /*
        Function name: Package::getTimeAsString

        Description: 
         An API to get a string describing the time of the deliver

        Parameters:
         None

        Return values:
         A string describing the time of the deliver
    */
    string getTimeAsString() const;

    /*
        Function name: Package::getIp

        Description: 
         An API to get a string describing the time of the deliver

        Parameters:
         None

        Return values:
         A string describing the ip address
    */
    string getIp() const;

    /*
        Function name: Package::getPort

        Description: 
         An API to get a string describing the time of the deliver

        Parameters:
         None

        Return values:
         The port number
    */
    uint16_t getPort() const;

    /*
        Function name: Package::getSize

        Description: 
         An API to get a string describing the time of the deliver

        Parameters:
         None

        Return values:
         The size of the package
    */
    uint64_t getSize() const;
};

#endif