#!/bin/bash

set -u

VM_NAME="rainfall"
VM_MEMORY=4096
VM_STORAGE=8000
VM_CPUS=4
VM_ISO="/mnt/nfs/homes/tsiguenz/sgoinfre/RainFall.iso"
VM_DISK="/mnt/nfs/homes/tsiguenz/sgoinfre/${VM_NAME}/${VM_NAME}_disk.vdi"

function delete_vm {
	if ! vboxmanage list vms | grep -q $VM_NAME; then
		echo "VM $VM_NAME does not exist!"
		exit
	fi
	echo "Deleting VM $VM_NAME!"
	vboxmanage controlvm $VM_NAME poweroff 2>/dev/null
	sleep 1
	vboxmanage unregistervm --delete $VM_NAME 2>/dev/null
	exit
}

function create_vm {
	if vboxmanage list vms | grep -q $VM_NAME; then
		echo "VM $VM_NAME already exist!"
		return
	fi
	echo "Creating VM $VM_NAME!"
	vboxmanage createvm --name $VM_NAME --register --basefolder '/tmp'
	vboxmanage modifyvm $VM_NAME --cpus $VM_CPUS --memory $VM_MEMORY
	# Hostonly
	vboxmanage modifyvm $VM_NAME --nic1 hostonly --hostonlyadapter1 vboxnet0
	# Nat with portforwarding
	# vboxmanage modifyvm $VM_NAME --nic1 nat --natpf1 "guestssh,tcp,127.0.0.1,2222,,22"

	vboxmanage createhd --filename $VM_DISK --size $VM_STORAGE --format VDI
	vboxmanage storagectl $VM_NAME --name "SATA Controller" --add sata --controller IntelAhci
	vboxmanage storageattach $VM_NAME --storagectl "SATA Controller" --port 0 --device 0 --type hdd --medium $VM_DISK
	# Storage for iso
	vboxmanage storagectl $VM_NAME --name "IDE Controller" --add ide --controller PIIX4
	vboxmanage storageattach $VM_NAME --storagectl "IDE Controller" --port 1 --device 0 --type dvddrive --medium $VM_ISO
	vboxmanage modifyvm $VM_NAME --boot1 dvd --boot2 disk
}

function run_vm {
	if vboxmanage list runningvms | grep -q $VM_NAME; then
		echo "VM $VM_NAME is already running!"
	else
		vboxmanage startvm rainfall
	fi
}

if [ "$#" -ne 0 ]; then
	if [ "$1" == "-r" ]; then
		delete_vm
	else
		echo "Invalid parameter, only -r is allowed!"
	fi
fi

create_vm
run_vm
