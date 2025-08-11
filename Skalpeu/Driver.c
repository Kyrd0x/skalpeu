#include <ntifs.h>
#include <ntddk.h>
#include <wdf.h>


// Variables globales
UNICODE_STRING DEVICE_NAME = RTL_CONSTANT_STRING(L"\\Device\\Skalpeu"); // Nom du device du driver
UNICODE_STRING SYM_LINK = RTL_CONSTANT_STRING(L"\\MyLink\\Skalpeu");        // Lien symbolique du device

void UnloadSkalpeuEDR(_In_ PDRIVER_OBJECT DriverObject) {
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "Skalpeu: Unloading routine called\n");
    // Suppression du device driver
    IoDeleteDevice(DriverObject->DeviceObject);
    // Suppression du lien symbolique
    IoDeleteSymbolicLink(&SYM_LINK);
}

NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "Skalpeu: Initializing the driver\n");

    NTSTATUS status;

    PDEVICE_OBJECT DeviceObject;
    UNICODE_STRING deviceName = DEVICE_NAME;
    UNICODE_STRING symlinkName = SYM_LINK;
    status = IoCreateDevice(
        DriverObject,
        0,
        &deviceName,
        FILE_DEVICE_UNKNOWN,
        0,
        FALSE,
        &DeviceObject
    );

    if (!NT_SUCCESS(status)) {
        DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "Skalpeu: Device creation failed\n");
        return status;
    }

    status = IoCreateSymbolicLink(
        &symlinkName,
        &deviceName
    );

    if (!NT_SUCCESS(status)) {
        DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "Skalpeu: Symlink creation failed\n");
        IoDeleteDevice(DeviceObject);
        return status;
    }

    DriverObject->DriverUnload = UnloadSkalpeuEDR;

    return status;
}
