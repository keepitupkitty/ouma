/*
 * Copyright 2023 rSec Linux
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _SYS_TTYDEFAULTS_H_
#define _SYS_TTYDEFAULTS_H_

/*
 * Defaults on "first" open.
 */
#define TTYDEF_IFLAG (BRKINT | ISTRIP | ICRNL | IMAXBEL | IXON | IXANY)
#define TTYDEF_OFLAG (OPOST | ONLCR | XTABS)
#define TTYDEF_LFLAG (ECHO | ICANON | ISIG | IEXTEN | ECHOE | ECHOKE | ECHOCTL)
#define TTYDEF_CFLAG (CREAD | CS7 | PARENB | HUPCL)
#define TTYDEF_SPEED (B9600)

/*
 * Control Character Defaults
 */
#define CTRL(x) (x & 037)
#define CEOF CTRL('d')
#ifdef _POSIX_VDISABLE
#define CEOL _POSIX_VDISABLE
#else
#define CEOL '\0' /* XXX avoid _POSIX_VDISABLE */
#endif
#define CERASE 0177
#define CINTR CTRL('c')
#ifdef _POSIX_VDISABLE
#define CSTATUS _POSIX_VDISABLE
#else
#define CSTATUS '\0' /* XXX avoid _POSIX_VDISABLE */
#endif
#define CKILL CTRL('u')
#define CMIN 1
#define CQUIT 034 /* FS, ^\ */
#define CSUSP CTRL('z')
#define CTIME 0
#define CDSUSP CTRL('y')
#define CSTART CTRL('q')
#define CSTOP CTRL('s')
#define CLNEXT CTRL('v')
#define CDISCARD CTRL('o')
#define CWERASE CTRL('w')
#define CREPRINT CTRL('r')
#define CEOT CEOF
/* compat */
#define CBRK CEOL
#define CRPRNT CREPRINT
#define CFLUSH CDISCARD

#endif /* !_SYS_TTYDEFAULTS_H_ */
