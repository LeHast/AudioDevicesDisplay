
#include <audioclient.h>
#include <audioendpoints.h>
#include <audioenginebaseapo.h>
#include <audioengineendpoint.h>
#include <audiopolicy.h>
#include <audiosessiontypes.h>
#include <devicetopology.h>
#include <endpointvolume.h>
#include <mmdeviceapi.h>
#include <spatialaudioclient.h>
#include <spatialaudiohrtf.h>
#include <spatialaudiometadata.h>

#include <iostream>
#include <Windows.h>

#include <functiondiscoverykeys_devpkey.h>

#pragma comment(lib, "Ole32.lib")


int main() {
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (SUCCEEDED(hr)) {
        IMMDeviceEnumerator* pEnum = NULL;
        hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnum);
        if (SUCCEEDED(hr)) {
            IMMDeviceCollection* pDevices;
            hr = pEnum->EnumAudioEndpoints(eCapture, DEVICE_STATE_ACTIVE, &pDevices);
            if (SUCCEEDED(hr)) {
                UINT count;
                pDevices->GetCount(&count);
                if (count == 0) {
                    std::cout << "No audio input devices found." << std::endl;
                }
                else {
                    for (UINT i = 0; i < count; i++) {
                        IMMDevice* pDevice;
                        hr = pDevices->Item(i, &pDevice);
                        if (SUCCEEDED(hr)) {
                            IPropertyStore* pStore;
                            hr = pDevice->OpenPropertyStore(STGM_READ, &pStore);
                            if (SUCCEEDED(hr)) {
                                PROPVARIANT friendlyName;
                                PropVariantInit(&friendlyName);
                                hr = pStore->GetValue(PKEY_Device_FriendlyName, &friendlyName);
                                if (SUCCEEDED(hr)) {
                                    std::wcout << "Audio Input Device " << i + 1 << ": " << friendlyName.pwszVal << std::endl;
                                    PropVariantClear(&friendlyName);
                                }
                                pStore->Release();
                            }
                            pDevice->Release();
                        }
                    }

                    std::cout << "Please enter the number of the device you want to select: ";
                    int deviceIndex;
                    std::cin >> deviceIndex;

                    if (deviceIndex < 1 || deviceIndex > count) {
                        std::cout << "Invalid device index." << std::endl;
                    }
                    else {
                        IMMDevice* pDevice;
                        hr = pDevices->Item(deviceIndex - 1, &pDevice);
                        if (SUCCEEDED(hr)) {
                            
                        


                        }// end if
                    }
                }
                pDevices->Release();
            }
            pEnum->Release();
        }
        CoUninitialize();
    }
    return 0;
}