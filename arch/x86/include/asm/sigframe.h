#ifndef _ASM_X86_SIGFRAME_H
#define _ASM_X86_SIGFRAME_H

#include <asm/sigcontext.h>
#include <asm/siginfo.h>
#include <asm/ucontext.h>
#include <linux/compat.h>

#ifdef CONFIG_X86_32
#define sigframe_ia32		sigframe
#define rt_sigframe_ia32	rt_sigframe
#define sigcontext_ia32		sigcontext
#define _fpstate_ia32		_fpstate
#define ucontext_ia32		ucontext
#else /* !CONFIG_X86_32 */

#ifdef CONFIG_IA32_EMULATION
#include <asm/ia32.h>
#endif /* CONFIG_IA32_EMULATION */

#endif /* CONFIG_X86_32 */

#if defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMULATION)
struct sigframe_ia32 {
	u32 pretcode;
	int sig;
	struct sigcontext_ia32 sc;
	/*
	 * fpstate is unused. fpstate is moved/allocated after
	 * retcode[] below. This movement allows to have the FP state and the
	 * future state extensions (xsave) stay together.
	 * And at the same time retaining the unused fpstate, prevents changing
	 * the offset of extramask[] in the sigframe and thus prevent any
	 * legacy application accessing/modifying it.
	 */
	struct _fpstate_ia32 fpstate_unused;
#ifdef CONFIG_IA32_EMULATION
	unsigned int extramask[_COMPAT_NSIG_WORDS-1];
#else /* !CONFIG_IA32_EMULATION */
	unsigned long extramask[_NSIG_WORDS-1];
#endif /* CONFIG_IA32_EMULATION */
	char retcode[8];
	/* fp state follows here */
};

struct rt_sigframe_ia32 {
	u32 pretcode;
	int sig;
	u32 pinfo;
	u32 puc;
#ifdef CONFIG_IA32_EMULATION
	compat_siginfo_t info;
#else /* !CONFIG_IA32_EMULATION */
	struct siginfo info;
#endif /* CONFIG_IA32_EMULATION */
	struct ucontext_ia32 uc;
	char retcode[8];
	/* fp state follows here */
};
#endif /* defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMULATION) */

#ifdef CONFIG_X86_64

struct rt_sigframe {
	char __user *pretcode;
	struct ucontext uc;
	struct siginfo info;
	/* fp state follows here */
};

#ifdef CONFIG_X86_X32_ABI

struct ucontext_x32 {
	unsigned int	  uc_flags;
	unsigned int 	  uc_link;
	compat_stack_t	  uc_stack;
	unsigned int	  uc__pad0;     /* needed for alignment */
	struct sigcontext uc_mcontext;  /* the 64-bit sigcontext type */
	compat_sigset_t	  uc_sigmask;	/* mask last for extensibility */
};

struct rt_sigframe_x32 {
	u64 pretcode;
	struct ucontext_x32 uc;
	compat_siginfo_t info;
	/* fp state follows here */
};

#endif /* CONFIG_X86_X32_ABI */

#endif /* CONFIG_X86_64 */

#endif /* _ASM_X86_SIGFRAME_H */
