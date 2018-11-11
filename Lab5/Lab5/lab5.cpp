

#define RANDOMIZE_CALLEE_REGISTERS __asm mov ebx, 0xAFAFAFAF \
                                   __asm mov esi, 0xAFAFAFAF \
                                   __asm mov edi, 0xAFAFAFAF 
#define RANDOMIZE_CALLER_REGISTERS __asm mov eax, 0xAFAFAFAF \
                                   __asm mov ecx, 0xAFAFAFAF \
                                   __asm mov edx, 0xAFAFAFAF

/***********************************************************************************************

    PART 1: Image Rotation

************************************************************************************************/
void imageRotation(unsigned int* image, int dim, int n) {
    unsigned int a0, a90, a180, a270;
    __asm 
    {
        // YOUR CODE STARTS HERE

		mov edi, n
		mov esi, image

		OUTER_LOOP:
			cmp edi, 0
			jle Finish

			mov ebx, 0			
			mov ecx, 0

			I_LOOP:
				mov edx, dim
				shr edx, 1
				cmp ebx, edx		
				jge EndI
				mov ecx, ebx		

			J_LOOP :				
				mov edx, dim		
				dec edx
				sub edx, ebx		
				cmp ecx, edx		
				jge I_LOOP_INCREASE	

				mov eax, ebx		
				MUL dim				
				add eax, ecx		
				mov edx, dword ptr[esi + 4 * eax] 
				mov a0, edx						 

				mov eax, ecx
				MUL dim
				mov edx, dim
				dec edx
				sub edx, ebx
				add eax, edx
				mov edx, dword ptr[esi + 4 * eax]
				mov a90, edx
				mov edx, a0
				mov dword ptr[esi + 4 * eax], edx

				mov edx, dim	
				dec edx			
				sub edx, ebx		
				mov eax, edx		
				MUL dim				
				mov edx, dim		
				dec edx				
				sub edx, ecx		
				add eax, edx		
				mov edx, dword ptr[esi + 4 * eax]
				mov a180, edx
				mov edx, a90
				mov dword ptr[esi + 4 * eax], edx

				mov edx, dim		
				dec edx				
				sub edx, ecx		
				mov eax, edx		
				MUL dim				
				add eax, ebx		
				mov edx, dword ptr[esi + 4 * eax]
				mov a270, edx
				mov edx, a180
				mov dword ptr[esi + 4 * eax], edx

				mov eax, ebx
				MUL dim
				add eax, ecx
				mov edx, a270
				mov dword ptr[esi + 4 * eax], edx

				inc ecx
				jmp J_LOOP


				I_LOOP_INCREASE:
					inc ebx
					jmp I_LOOP
				
			EndI:       
				dec edi
				jmp OUTER_LOOP

		Finish:
		
		//YOUR CODE ENDS HERE

    }
}

/***********************************************************************************************

PART 2: Selection Sort

************************************************************************************************/
__declspec(naked)
int findMinIndex(int integer_array[], int i, int j)
{

	// C code to be converted to x86 assembly
	/*
	int iMin = i;
	// test against elements after i and before j to find the smallest
	for ( i ; i < j; i++) {
	// if this element is less, then it is the new minimum
	if (integer_array[i] < integer_array[iMin]) {
	// found new minimum; remember its index
	iMin = i;
	}
	}

	return iMin;
	*/

	RANDOMIZE_CALLER_REGISTERS

		__asm
	{
		// YOUR CODE STARTS HERE
		push ebp

		mov ebp, esp
		push edi
		push esi
		mov eax, j
		mov ebx, i
		mov ecx, integer_array
		mov edx, ebx

		LOOP1:
			cmp ebx, eax
			jge ENDLOOP1

			mov esi, [ecx + 4 * ebx]
			mov edi, [ecx + 4 * edx]

			cmp esi, edi
			jge NEXT

			mov edx, ebx

			NEXT:
				inc ebx
				jmp LOOP1
		
			ENDLOOP1:
				mov ecx, edx
				pop esi
				pop edi
				mov esp, ebp
				pop ebp

		
		// YOUR CODE ENDS HERE
		ret
	}

}

void selectionSort(int integer_array[], int array_size)
{

	// C code to be converted to x86 assembly
	/*
	int j;
	int iMin;
	int temp;

	// advance the position through the entire array //
	// (could do j < n-1 because single element is also min element) //
	for (j = 0; j < array_size-1; j++) {

	// find the index of min element in the unsorted a[j .. n-1] //
	iMin = findMinIndex (integer_array, j, array_size);

	if(iMin != j) { // swap values
	temp = integer_array[iMin];
	integer_array[iMin] = integer_array [j];
	integer_array[j] = temp;
	}
	}
	*/

	RANDOMIZE_CALLEE_REGISTERS
	RANDOMIZE_CALLER_REGISTERS

		__asm
	{
		// YOUR CODE STARTS HERE
		
		mov eax, [ebp + 12]
		mov esi, [ebp + 8]

		mov edi, 0
		dec eax

		LOOP1:
			cmp eax, edi
			jl ENDLOOP1

			mov ebx, [ebp + 12]
			push ebx
			push edi
			push esi

			call findMinIndex
			add esp, 12
			mov ebx, edx
			
			cmp edi, ebx
			je NEXT

			mov edx, [esi + 4 * ebx]
			mov ecx, [esi + 4 * edi]
			xor edx, ecx
			xor ecx, edx
			xor edx, ecx

			mov [esi + 4 * ebx], edx
			mov [esi + 4 * edi], ecx

			NEXT:
				inc edi
				jmp LOOP1
		
		ENDLOOP1:
			mov [ebp + 8], esi

		// YOUR CODE ENDS HERE
	}

}