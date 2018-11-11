#define RANDOMIZE_CALLEE_REGISTERS __asm mov ebx, 0xAFAFAFAF \
                                   __asm mov esi, 0xAFAFAFAF \
                                   __asm mov edi, 0xAFAFAFAF 
#define RANDOMIZE_CALLER_REGISTERS __asm mov eax, 0xAFAFAFAF \
                                   __asm mov ecx, 0xAFAFAFAF \
                                   __asm mov edx, 0xAFAFAFAF

/***********************************************************************************************

PART 1: Image Thresholding

************************************************************************************************/
__declspec(naked)
void imageThresholding(unsigned char* image, int dim, unsigned char threshold) {
	RANDOMIZE_CALLER_REGISTERS
	__asm
	{
		// YOUR CODE STARTS HERE
		push ebp
		mov ebp, esp

		sub esp, 4

		push edi 
		push esi 
		push ebx

		mov ebx, [ebp + 8]		//First parameter - image
		//mov ecx, [ebp + 12]		//Second parameter - dim
		//mov edi, [ebp + 16]		Third parameter - threshold

		mov esi, 0				//i
		mov edi, 0				//j

		I_LOOP:
			mov ecx, [ebp +  12]
			cmp esi, ecx
			jge ENDI
			mov edi, 0

			J_LOOP:
			
				mov ecx, [ebp + 12]
				cmp edi, ecx
				jge I_LOOP_INCREASE

				mov eax, esi
				MUL ecx
				add eax, edi

				mov dl, byte ptr[ebx + eax]
				xor ecx, ecx
				mov cl, [ebp + 16]
				
				cmp dl, cl
				jae WHITE

				xor edx, edx
				mov dl, 0x00
				mov byte ptr[ebx + eax], dl
				jmp NEXT

				WHITE:
					xor edx, edx				
					mov dl, 0xFF
					mov byte ptr[ebx + eax], dl

				NEXT:
					inc edi
					jmp J_LOOP

		I_LOOP_INCREASE:
			inc esi
			jmp I_LOOP

		ENDI:

		pop ebx
		pop esi
		pop edi

		mov esp, ebp

		pop ebp
		

		ret
		// YOUR CODE ENDS HERE
	}
}

/***********************************************************************************************

PART 2: Binary Search

************************************************************************************************/
__declspec(naked)
int binarySearch(int integer_array[], int toFind, int start_i, int end_i)
{
	// C code to be converted to x86 assembly
	/*
	int binary_search(int *data, int toFind, int start, int end){
    //Get the midpoint.
    int mid = start + (end - start)/2;   //Integer division

    //Stop condition.
    if (start > end)
       return -1;
    else if (data[mid] == toFind)        //Found?
       return mid;
    else if (data[mid] > toFind)         //Data is greater than toFind, search lower half
       return binary_search(data, toFind, start, mid-1);
    else                                 //Data is less than toFind, search upper half
       return binary_search(data, toFind, mid+1, end);
	}
	*/
	RANDOMIZE_CALLER_REGISTERS
		__asm
	{
		// YOUR CODE STARTS HERE
		push ebp
		mov ebp, esp

		push edi
		push esi
		push ebx

		mov esi, [ebp + 16]		//start
		mov edi, [ebp + 20]		//end
		mov ebx, [ebp + 8]		//integer array
		
		mov eax, edi		//move end to eax
		sub eax, esi        //subtract eax by start
		xor edx, edx
		mov ecx, 2
		DIV ecx
		add eax, esi		//eax = mid
		
		CONDITION1:
			cmp esi, edi	//compare start > end
			jle CONDITION2	// if start <= end jmp to CONDITION2
			mov eax, -1		//mov -1 to eax to return 
			jmp END

		CONDITION2:
			mov edx, dword ptr[ebx + 4 * eax]		//edx is integer_array[mid]
			mov ecx, [ebp + 12]					//ecx = toFind
			cmp edx, ecx						//compare edx == ecx
			jne CONDITION3						//if edx != ecx jump to CONDITION3
			jmp END		//if edx==ecx jump to END

		CONDITION3:
			cmp edx, ecx	// compare edx(integer_array[mid]) and ecx(toFind)
			jle ELSE		//if edx <= ecx jump to ELSE

			//CALLLER CONVENTION
			push eax
			push ecx
			push edx
			
			dec eax		//eax(mid) - 1
			push eax	//push mid-1 (last parameter) into stack
			push esi	//push start (third parameter) into stack
			push ecx	//push toFind (second parameter) into stack
			push ebx	//push integer_array (first parameter) into stack
			
			call binarySearch

			add esp, 16
			mov ebx, eax
			pop edx
			pop ecx
			pop eax
			mov eax, ebx
			jmp END

		ELSE:
			//CALLER CONVENTION
			push eax
			push ecx
			push edx

			inc eax		//eax (mid) + 1
			push edi	//push end (last parameter) into stack
			push eax	//push mid+1 (third parameter) into stack
			push ecx	//push toFind (second parameter) into stack
			push ebx	//push integer_array (first parameter) into stack

			call binarySearch

			add esp, 16

			mov ebx, eax

			pop edx
			pop ecx
			pop eax

			mov eax, ebx

		END:

		pop ebx 
		pop esi
		pop edi

		mov esp, ebp
		pop ebp

		ret
		// YOUR CODE ENDS HERE
	}

}


/***********************************************************************************************
Part 3: Image Averaging
Your task will be to apply averaging to an image. We will be using k=1, which means you will 
add all the adjacent neighbors. Remember to include the value of the target pixel as well. 
Take into account that pixels that are on the edges won’t have all 8 neighbors, so your code 
should be able to account for that. 
- Your computed value should be in image_out, do not modify the values of image.
- The width and height of the image are equal to dim.
***********************************************************************************************/

__declspec(naked)
void imageAveraging(unsigned char* image, int dim, unsigned char* image_out){
	RANDOMIZE_CALLER_REGISTERS
		__asm
	{
		// YOUR CODE STARTS HERE
		push ebp
		mov ebp, esp

		push edi
		push esi
		push ebx

		mov esi, 0		//i
		mov edi, 0		//j

		I_LOOP:
			mov edx, [ebp + 12]
			cmp esi, edx
			jge ENDI
			mov edi, 0

			J_LOOP:
				mov edx, [ebp + 12]
				cmp edi, edx
				jge I_LOOP_INCREASE

				dec edx

				cmp esi, 0
				je I_ZERO

				cmp esi, edx
				je I_DIM

				cmp edi, 0
				je J_ZERO

				cmp edi, edx
				je J_DIM

				
				NINE:
					//ORIGINAL OFFSET - STORE IN EBX
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi			
					mov edx, [ebp + 8]
					xor ebx, ebx
					mov bl, byte ptr[edx + eax]

					//MID-LEFT
					dec eax					
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx			

					//MID-RIGHT
					add eax, 2					
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//UP-MID
					mov eax, esi			
					dec eax
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi			
					mov edx, [ebp + 8]
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//UP-LEFT CORNER
					dec eax					
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//UP-RIGHT CORNER
					add eax, 2				
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//LOW-MID
					mov eax, esi			
					inc eax
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi			
					mov edx, [ebp + 8]
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx
				
					//LOW-LEFT CORNER
					dec eax					
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx
					
					//LOW-RIGHT CORNER
					add eax, 2					
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//CALCULATE AVERAGE
					mov eax, ebx
					mov ecx, 9
					xor edx, edx
					DIV ecx
					mov ebx, eax

					//CALCULATE ORIGINAL OFFSET + MOVE TO NEW IMAGE
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi			
					mov edx, [ebp + 16]
					mov byte ptr[edx + eax], bl

					jmp J_LOOP_INCREASE
				
				I_ZERO:
					cmp edi, 0
					je I_ZERO_J_ZERO

					mov edx, [ebp + 12]
					dec edx
					cmp edi, edx
					je I_ZERO_J_DIM

					//ORIGINAL OFFSET - STORE IN EBX
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi			
					mov edx, [ebp + 8]
					xor ebx, ebx
					mov bl, byte ptr[edx + eax]

					//MID-LEFT
					dec eax					//GET MIDDLE LEFT OFFSET
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx			//GET THE SUM

					//MID-RIGHT
					add eax, 2					//GET MIDDLE RIGHT OFFSET
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//LOW-MID
					mov eax, esi			//MOVE i into EAX
					inc eax
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi			//GET MIDDLE LOWER OFFSET

					mov edx, [ebp + 8]
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//LOW LEFT CORNER
					dec eax					//GET LOWER LEFT CORNER OFFSET
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//LOW RIGHT CORNER
					add eax, 2					//GET LOWER RIGHT CORNER OFFSET
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//CALCULATE AVERAGE
					mov eax, ebx
					mov ecx, 6
					xor edx, edx
					DIV ecx
					mov ebx, eax

					//CALCULATE ORIGINAL OFFSET + MOVE TO NEW IMAGE
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 16]
					mov byte ptr[edx + eax], bl

					jmp J_LOOP_INCREASE

				I_DIM:
					cmp edi, 0
					je I_DIM_J_ZERO

					mov edx, [ebp + 12]
					dec edx
					cmp edi, edx
					je I_DIM_J_DIM

					//ORIGINAL OFFSET - STORE IN EBX
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 8]
					xor ebx, ebx
					mov bl, byte ptr[edx + eax]

					//MID-LEFT
					dec eax					
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx			

					//MID-RIGHT
					add eax, 2					
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//UP-MID
					mov eax, esi
					dec eax
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 8]
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//UP-LEFT CORNER
					dec eax
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//UP-RIGHT CORNER
					add eax, 2
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//CALCULATE AVERAGE
					mov eax, ebx
					mov ecx, 6
					xor edx, edx
					DIV ecx
					mov ebx, eax

					//CALCULATE ORIGINAL OFFSET + MOVE TO NEW IMAGE
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 16]
					mov byte ptr[edx + eax], bl

					jmp J_LOOP_INCREASE

				J_ZERO:

					//ORIGINAL OFFSET - STORE IN EBX
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 8]
					xor ebx, ebx
					mov bl, byte ptr[edx + eax]

					//MID-RIGHT
					inc eax
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//UP-MID
					mov eax, esi
					dec eax
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 8]
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//UP-RIGHT CORNER
					inc eax
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//LOW-MID
					mov eax, esi
					inc eax
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 8]
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//LOW-RIGHT CORNER
					inc eax
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//CALCULATE AVERAGE
					mov eax, ebx
					mov ecx, 6
					xor edx, edx
					DIV ecx
					mov ebx, eax

					//CALCULATE ORIGINAL OFFSET + MOVE TO NEW IMAGE
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 16]
					mov byte ptr[edx + eax], bl

					jmp J_LOOP_INCREASE
					
				J_DIM:
					//ORIGINAL OFFSET - STORE IN EBX
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 8]
					xor ebx, ebx
					mov bl, byte ptr[edx + eax]

					//MID-LEFT
					dec eax
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//UP-MID
					mov eax, esi
					dec eax
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 8]
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//UP-LEFT CORNER
					dec eax
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//LOW-MID
					mov eax, esi
					inc eax
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 8]
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//LOW-LEFT CORNER
					dec eax
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//CALCULATE AVERAGE
					mov eax, ebx
					mov ecx, 6
					xor edx, edx
					DIV ecx
					mov ebx, eax

					//CALCULATE ORIGINAL OFFSET + MOVE TO NEW IMAGE
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 16]
					mov byte ptr[edx + eax], bl

					jmp J_LOOP_INCREASE

				I_ZERO_J_ZERO:
					//ORIGINAL OFFSET - STORE IN EBX
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 8]
					xor ebx, ebx
					mov bl, byte ptr[edx + eax]

					//MID-RIGHT
					inc eax
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//LOW-MID
					mov eax, esi
					inc eax
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 8]
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//LOW-RIGHT CORNER
					inc eax
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//CALCULATE AVERAGE
					mov eax, ebx
					mov ecx, 4
					xor edx, edx
					DIV ecx
					mov ebx, eax

					//CALCULATE ORIGINAL OFFSET + MOVE TO NEW IMAGE
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 16]
					mov byte ptr[edx + eax], bl

					jmp J_LOOP_INCREASE

				I_ZERO_J_DIM:

					//ORIGINAL OFFSET - STORE IN EBX
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 8]
					xor ebx, ebx
					mov bl, byte ptr[edx + eax]

					//MID-LEFT
					dec eax
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//LOW-MID
					mov eax, esi
					inc eax
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 8]
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//LOW-LEFT CORNER
					dec eax
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//CALCULATE AVERAGE
					mov eax, ebx
					mov ecx, 4
					xor edx, edx
					DIV ecx
					mov ebx, eax

					//CALCULATE ORIGINAL OFFSET + MOVE TO NEW IMAGE
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 16]
					mov byte ptr[edx + eax], bl

					jmp J_LOOP_INCREASE

				I_DIM_J_ZERO:

					//ORIGINAL OFFSET - STORE IN EBX
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 8]
					xor ebx, ebx
					mov bl, byte ptr[edx + eax]

					//MID-RIGHT
					inc eax
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//UP-MID
					mov eax, esi
					dec eax
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 8]
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//UP-RIGHT CORNER
					inc eax
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//CALCULATE AVERAGE
					mov eax, ebx
					mov ecx, 4
					xor edx, edx
					DIV ecx
					mov ebx, eax

					//CALCULATE ORIGINAL OFFSET + MOVE TO NEW IMAGE
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 16]
					mov byte ptr[edx + eax], bl

					jmp J_LOOP_INCREASE

				I_DIM_J_DIM:

					//ORIGINAL OFFSET - STORE IN EBX
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 8]
					xor ebx, ebx
					mov bl, byte ptr[edx + eax]

					//MID-LEFT
					dec eax
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//UP-MID
					mov eax, esi
					dec eax
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 8]
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx

					//UP-LEFT CORNER
					dec eax
					xor ecx, ecx
					mov cl, byte ptr[edx + eax]
					add ebx, ecx


					//CALCULATE AVERAGE
					mov eax, ebx
					mov ecx, 4
					xor edx, edx
					DIV ecx
					mov ebx, eax

					//CALCULATE ORIGINAL OFFSET + MOVE TO NEW IMAGE
					mov eax, esi
					mov edx, [ebp + 12]
					MUL edx
					add eax, edi
					mov edx, [ebp + 16]
					mov byte ptr[edx + eax], bl

					jmp J_LOOP_INCREASE
									
				J_LOOP_INCREASE:
					inc edi
					jmp J_LOOP

		I_LOOP_INCREASE:
			inc esi
			jmp I_LOOP

		ENDI:
			
		pop ebx
		pop esi
		pop edi

		mov esp, ebp
		pop ebp

		ret
		// YOUR CODE ENDS HERE
	}
}
